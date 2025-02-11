package view;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Set;

import javax.swing.*;

import controllers.HospedeController;
import controllers.MainController;
import dto.HospedeDto;
import exception.HospedeException;

public class HospedeView extends JFrame {

    private static final long serialVersionUID = -3843327249763458447L;

    private HospedeController hospedeController;
    private JTextField cpfField;
    private JTextField nameField;
    private JTextField emailField;
    private JTextField phoneField;
    private JList<String> hospedeList;
    private JTextField searchCpfField;
    private JTextArea hospedeDetailsArea;

    public HospedeView() {
        hospedeController = MainController.getHospedeController();
        setTitle("Hospede");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Create Hospede", createCreatePanel());
        tabbedPane.addTab("Listar Hospedes", createViewPanel());
        tabbedPane.addTab("Buscar Hospede", createSearchPanel());

        add(tabbedPane);
    }

    private JPanel createCreatePanel() {
        JPanel createPanel = new JPanel();
        createPanel.setLayout(new GridLayout(5, 2));

        createPanel.add(new JLabel("CPF:"));
        cpfField = new JTextField();
        createPanel.add(cpfField);

        createPanel.add(new JLabel("Name:"));
        nameField = new JTextField();
        createPanel.add(nameField);

        createPanel.add(new JLabel("Email:"));
        emailField = new JTextField();
        createPanel.add(emailField);

        createPanel.add(new JLabel("Phone:"));
        phoneField = new JTextField();
        createPanel.add(phoneField);

        JButton createButton = new JButton("Create");
        createPanel.add(createButton);

        createButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                createHospede();
            }
        });

        return createPanel;
    }

    private JPanel createViewPanel() {
        JPanel viewPanel = new JPanel();
        viewPanel.setLayout(new BorderLayout());

        hospedeList = new JList<>();
        viewPanel.add(new JScrollPane(hospedeList), BorderLayout.CENTER);

        JButton refreshButton = new JButton("Refresh");
        viewPanel.add(refreshButton, BorderLayout.SOUTH);

        refreshButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                refreshHospedes();
            }
        });

        return viewPanel;
    }

    private JPanel createSearchPanel() {
        JPanel searchPanel = new JPanel();
        searchPanel.setLayout(new BorderLayout());

        JPanel inputPanel = new JPanel();
        inputPanel.setLayout(new GridLayout(2, 2));
        inputPanel.add(new JLabel("CPF:"));
        searchCpfField = new JTextField();
        inputPanel.add(searchCpfField);

        JButton searchButton = new JButton("Buscar Hospedes");
        inputPanel.add(searchButton);

        searchPanel.add(inputPanel, BorderLayout.NORTH);

        hospedeDetailsArea = new JTextArea();
        hospedeDetailsArea.setEditable(false);
        searchPanel.add(new JScrollPane(hospedeDetailsArea), BorderLayout.CENTER);

        searchButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                searchHospede();
            }
        });

        return searchPanel;
    }

    private void createHospede() {
        try {
            String cpf = cpfField.getText();
            String name = nameField.getText();
            String email = emailField.getText();
            long phone = Long.parseLong(phoneField.getText());
            HospedeDto hospedeDto = new HospedeDto(cpf, name, email, phone);
            hospedeController.createHospede(hospedeDto);
            MainController.save();
            JOptionPane.showMessageDialog(null, "Hospede created successfully!");
        } catch (HospedeException ex) {
            JOptionPane.showMessageDialog(null, "Erro: " + ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void refreshHospedes() {
        Set<String> hospedes = hospedeController.getHospedes();
        hospedeList.setListData(hospedes.toArray(new String[0]));
    }

    private void searchHospede() {
        try {
            String cpf = searchCpfField.getText();
            HospedeDto hospedeDto = hospedeController.getHospedeDto(cpf);
            hospedeDetailsArea.setText(hospedeDto.toString());
        } catch (HospedeException ex) {
            hospedeDetailsArea.setText("Error: " + ex.getMessage());
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }
}